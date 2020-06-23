#include "PathfinderMgr.h"

PathfinderMgr::PathfinderMgr()
    : m_editState(EditState::None),
      m_traverseGrid(TraverseGrid::Type::Square, sf::FloatRect(-Camera::GetOffset(), sf::Vector2f(static_cast<float>(Window::GetWidth()) - 200.0f, static_cast<float>(Window::GetHeight()))))

{
    m_pathfinders.emplace_back(std::make_unique<AStar>());

    for (auto &pathfinder : m_pathfinders)
    {
        pathfinder->SetTraverseGrid(&m_traverseGrid);
        pathfinder->AssignNodes(m_traverseGrid.GetNodes());
    }
}

void PathfinderMgr::Update()
{
    if (Mouse::IsDown(sf::Mouse::Button::Left) && Mouse::GetPos().x < static_cast<float>(Window::GetWidth() - 200))
    {
        long nodeUID = m_traverseGrid.GetNodeUIDByPosition(Camera::ScreenToWorld(Mouse::GetPos()));
        switch (m_editState)
        {
        case EditState::AddObstacles:
            m_traverseGrid.SetIsObstacle(nodeUID, true);
            break;
        case EditState::RemObstacles:
            m_traverseGrid.SetIsObstacle(nodeUID, false);
            break;
        case EditState::SetStart:
            m_traverseGrid.SetStart(nodeUID);
            break;
        case EditState::SetGoal:
            m_traverseGrid.SetGoal(nodeUID);
            break;
        default:
            break;
        }
    }
}

void PathfinderMgr::DrawGrid()
{
    m_traverseGrid.Draw();
}

void PathfinderMgr::DrawPathfinders()
{
    for (auto &pathfinder : m_pathfinders)
    {
        pathfinder->DrawAnticipation();
        pathfinder->DrawViaConnections();
        if (pathfinder->IsDone())
            pathfinder->DrawResult();
    }
}

void PathfinderMgr::Start()
{
    for (auto &pathfinder : m_pathfinders)
        pathfinder->Start();
}

void PathfinderMgr::Pause()
{
    for (auto &pathfinder : m_pathfinders)
        pathfinder->Pause();
}

void PathfinderMgr::Resume()
{
    for (auto &pathfinder : m_pathfinders)
        pathfinder->Resume();
}

void PathfinderMgr::Restart()
{
    for (auto &pathfinder : m_pathfinders)
        pathfinder->Restart();
}

void PathfinderMgr::Reset()
{
    for (auto &pathfinder : m_pathfinders)
        pathfinder->Reset();
}

void PathfinderMgr::SetSleepDelay(sf::Time delay) noexcept
{
    for (auto &pathfinder : m_pathfinders)
        pathfinder->SetSleepDelay(delay);
}

void PathfinderMgr::Activate(const std::string &name)
{
}

void PathfinderMgr::Deactivate(const std::string &name)
{
}