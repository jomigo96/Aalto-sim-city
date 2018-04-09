#ifndef PATH_HPP
#define PATH_HPP

/*!
 * \file Path.hpp
 * \brief Map class
 * \author Group 2
 */

#include <stack>
#include "Position.hpp"
/*!
 * \class Path
 * \brief Path taken by a vehicle
 *
 *  The vehicle's path consists of a stack of positions
 */
class Path {
public:

	/*!
     *  \brief Default contructor
     */
    Path();
    
    
    /*!
     *  \brief Constructor
     * 
     *  \param src Pointer to the starting position
     *  \param dst Pointer to the destination position
     */
    Path(Position* src, Position* dst);
    
    
    /*!
     *  \brief Destructor
     */
    virtual ~Path();
    
    
    
    /*!
     *  \brief Adds a node to the Path
     * 
     *  Node should be added from last to first.
     * 
     * \param pos Pointer to the position to be added
     */
    void addNode(Position* pos);
    
    
    
    /*!
     *  \brief Get the next node
     * 
     *  \return Node on top of the stack
     */
    Position* nextNode();
    
    
    
    /*!
     *  \brief Removes the current node from the stack
     */
    void removeCurrentNode();
    
    
    /*!
     *  \brief Prints the path on the console
     * 
     *  Used for testing purposes
     */
    void print() const;
    
    
    
    /*!
     *  \brief Checks if the path is complete
     * 
     *  \return Boolean
     */
    bool isEmpty() const;
    
    
    
    /*!
     *  \brief Checks the number of nodes in the path
     * 
     *  \return Size of the path
     */
    int getSize() const;
    
    
    
    //friend std::ostream& operator<<(std::ostream& out,Path path);
    
    
    
private:
    std::stack<Position*> m_path;
    Position* m_source;
    Position* m_destination;
};

#endif /* PATH_HPP */

