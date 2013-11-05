Welcome to TAEval Deliverable#2

Our system consists of a client process and a server process. They both run on the same machine and can communicate with eachother to perform certain API calls. Currently only 5 of our 9 API function calls work and those are: Login, Logout, View TAs, View Courses, and Delete Task.

Login: We have a pre-determined username for logging in and out so when you run the login test, the client sends the username to the server, which will check to make sure it exists, and returns with a message saying whether or not it is valid. If it is valid, the user is logged into the system. NOTE: This must be run before any other function as you can't do anything if you aren't logged in!

Logout: This function sends a message to the server telling it that the client is finished and is closing the port. The server then frees it's port for other connections. NOTE: You cannot log out twice. In a final version of the system the program would not allow you to try to log out twice.

View TAs: This sends a Course number to the server which will check the database for all the TAs and return all the TAs associated with that course.

View Courses: This funtion call sends the username of the Instructor using the system and the system returns all the courses that the Instructor is teaching.

Delete Task: This call takes a Task Name as a parameter and will delete that task. In this version, you can only run this test once because we don't have a working insert function so once it is deleted it is gone. There is an additional folder on the CD named 'Storage' that contains the flat files needed to replenish the database after each deletion.

A few things to know:
-The Storage folder must be in the same directory as the executable for the server(IMPORTANT) When compiled with QT Creator you must put the storage folder in with the executable in the build folder
-When recompiling our code we had a brief issue where it would only run properly if it was in the 'home' folder in ubuntu so if there are any issues recompiling that may be the reason. 
-Our database is composed of 5 binary trees that we wrote and are stored within an array. We did this to ensure that searching would be quick and efficient.

Thanks!

-A team with a clever name
