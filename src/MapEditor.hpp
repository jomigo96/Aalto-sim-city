#ifndef MAPEDITOR_HPP
#define MAPEDITOR_HPP

/*!
 * \file MapEditor.hpp
 * \brief MapEditor class
 * \author Group 2
 */


/*!
 * \brief Number of pixels for the map editor width
 */
#define MAP_EDITOR_WIDTH 250

#include "Map.hpp"

/*!
 * \class MapEditor
 * \brief Class interacting with the map
 *
 *  This class can add or delete MapItem instances to the map.
 *  Moreover, it can change the speed of the animation and the intensity of traffic.
 */
class MapEditor : public sf::Drawable {
public:
    static const int WAITING = 0; /*!< Waiting for a key to be pressed */
    static const int ROAD_SOURCE_1 = 1; /*!< Set source 1 of a Road */
    static const int ROAD_DESTINATION_1 = 2; /*!< Set destination 1 of a Road */
    static const int ROAD_SOURCE_2 = 3; /*!< Set source 2 of a Road */
    static const int ROAD_DESTINATION_2 = 4; /*!< Set destination 2 of a Road */
    static const int INTERSECTION = 5; /*!< Set intersection */
    static const int PARKING = 6; /*!< Set parking */
    static const int BUILDING = 7; /*!< Set building */
    
    /*!
     * \brief Constructor
     */
    MapEditor(sf::RenderTexture& texture, Map& map, sf::Font);
    
    /*!
     * \brief Destructor
     */
    virtual ~MapEditor();
    
    /*!
     * \brief Set the current status
     * 
     * \param status Status to be set
     */
    void setStatus(int status);
    
    /*!
     * \brief Return the current status
     */
    int getStatus() const;
    
    /*!
     * \brief Create a MapItem according to the current status
     * 
     * \param position Pointer of the position where the MapItem will be added
     */
    void create(Position* position);
    
    /*!
     * \brief Delete a MapItem according to its position
     * 
     * \param position Pointer of the position where the MapItem will be removed
     */
    void deleteItem(Position* position);
    
    /*!
     * \brief Update the speed of the simulation and the intensity of the traffic
     * 
     * \param speed Speed of the simulation
     * \param intensity Intensity of the traffic
     */
    void setFactors(float speed, float intensity);
    
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void init();
    
    sf::RenderTexture& m_texture;
    sf::Font m_font;
    sf::Text m_instructions_text;
    sf::Text m_status_text;
    
    int m_status = MapEditor::WAITING;
    Position* m_src1;
    Position* m_dst1;
    Position* m_src2;
    Position* m_dst2;
    Position* m_position;
    Map& m_map;
    
    
    float speed_factor;
    float traffic_intensity;
};

#endif /* MAPEDITOR_HPP */

