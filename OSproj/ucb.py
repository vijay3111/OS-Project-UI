from math import sqrt,log,floor
import numpy as np
import os

class Priority_Agent():
    
    def __init__(self):
        """
        This function initialises all the class attributes.
        The reward and punishment for this model are by default 0.2 and 0.2 respectively
        """
        self.item_count = 0
        self.reward_tray = []
        self.current_order = []
        self.no_of_increments = []
        self.no_of_updates = 0
        self.reward = 0.2
        self.punishment = 0.2
    
    def add_folder(self):
        """
        This method is to add the record of a new folder.
        """
        self.current_order.append(self.item_count)
        self.no_of_increments.append(1)
        self.reward_tray.append(0)
        self.item_count+=1
    
    def remove_folder(self,target_index):
        """
        Specify the original index(as in the GUI array) of the target_file for removal. 
        """
        del self.reward_tray[target_index]
        del self.no_of_increments[target_index]
        self.current_order.remove(target_index)
        self.current_order = list(map(lambda x: x-1 if x > target_index else x,current_order))
        self.item_count -= 1    
    
    def update(self,target_index):
        """
        Input the index of the user-selected application in the desktop to update the records.
        """
        self.reward_tray[target_index] += self.reward
        self.__punish(target_index)
        self.no_of_updates += 1
    
    def get_priority_list(self):
        """
        Get the new priority list with more importance given to the most 
        recent update. This priority list can be directly taken with reference to the
        current GUI array
        """
        if self.no_of_updates == 0:
            return self.current_order
        
        max_upper_bound = 0
        target_index = -1
        for i in range(0,self.item_count):
            r_i = self.reward_tray[i]/self.no_of_increments[i]
            delta_i = sqrt( (3*log(self.no_of_updates))/(2*self.no_of_increments[i]) )
            upper_bound = r_i + delta_i
            
            if upper_bound > max_upper_bound:
                max_upper_bound = upper_bound
                target_index = i
        
        current_pos = self.current_order.index(target_index)
        target_pos = floor(current_pos/2)
        for i in range(current_pos,target_pos,-1):
            self.current_order[i],self.current_order[i-1] = \
                self.current_order[i-1],self.current_order[i]
        
        return self.current_order
    
    def __punish(self,target_index):
        """
        This private method is to punish all the applications which have been updated
        previously so as to add more flexibility to the model.
        """
        location = self.current_order.index(target_index)
        for i in range(location):
            if self.reward_tray[self.current_order[i]] > self.punishment:
                self.reward_tray[self.current_order[i]] -= self.punishment
            else:
                self.reward_tray[self.current_order[i]] = 0 
my_agent = Priority_Agent()

with open('folderfile') as f:
    my_folder_list = [my_folder_list.rstrip() for my_folder_list in f]
f.close()
my_folder_list = np.array(my_folder_list)
for item in my_folder_list:
    my_agent.add_folder()

priority_list = my_agent.get_priority_list()
ordered_items = my_folder_list[priority_list]
print('The list looks like:')
for item in ordered_items:
    print(item) 
folder_choice = input('Enter the selected choice: ')  
folder_choice = np.where(my_folder_list == folder_choice)[0][0]
my_agent.update(folder_choice)
priority_list = my_agent.get_priority_list()
ordered_items = my_folder_list[priority_list]
print('The revised list looks like:')
openfile= open("folderfile","w")
for item in ordered_items:
    print(item)
    openfile.write(item+"\n")
openfile.close()
os.system('g++ resetlist.cpp')
os.system('./a.out')
